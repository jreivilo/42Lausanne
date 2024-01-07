import { Injectable } from '@nestjs/common';
import { PrismaService } from 'src/prisma/prisma.service';
import { HttpService } from '@nestjs/axios';
import { Tournaments, Games, Aliases, Users } from '@prisma/client';
import { TStatus } from '@prisma/client';
import { PlayerScore, PendingGame, Alias } from './tournament.gateway';

@Injectable()
export class TournamentService {
	constructor(private prisma: PrismaService, private httpService: HttpService) {}

	async getAllTournaments(): Promise<Tournaments[]> {
		const tournaments = await this.prisma.tournaments.findMany();
		return (tournaments);
	}

	async getLastTournament(): Promise<Tournaments> {
		const tournaments = await this.getAllTournaments();
		return tournaments[tournaments.length - 1];
	}

	async createTournament(): Promise<Tournaments> {
		const tournament = await this.prisma.tournaments.create({
			data: {
				status: TStatus.not_started,
			},
		});
		console.log("Tournament create: ", tournament);
		return tournament;
	}

	async getScores(): Promise<PlayerScore[]> {
		var scores: PlayerScore[] = [];
		const players: Users[] = await this.lastTournamentPlayers();
		const games: Games[] = await this.lastTournamentGames();
		for (const p of players) {
			const alias = await this.getAlias(p.id);
			var s: PlayerScore = {
				alias: null,
				games_played: 0,
				games_won: 0,
				games_lost: 0,
				points: 0,
			};
			for (const g of games) {
				if (g.user1Id === p.id) {
					s.points += g.user1Score;
					s.games_played += 1;
					if (g.user1Score > g.user2Score) {
						s.games_won += 1;
					} else {
						s.games_lost += 1;
					}
				}
				if (g.user2Id === p.id) {
					s.points += g.user2Score;
					s.games_played += 1;
					if (g.user1Score < g.user2Score) {
						s.games_won += 1;
					} else {
						s.games_lost += 1;
					}
				}
			}
			s.alias = alias?.alias;
			scores.push(s);
		}
		scores.sort((a, b) => {
			return (b.points - a.points);
		});
		return scores;
	}

	async lastTournamentPlayers(): Promise<Users[]> {
		const last_tournament = await this.getLastTournament();
		if (!last_tournament) {
			console.log("lastTournamentPlayers: no valid tournament");
			return [];
		}
		const players: Users[] = await this.prisma.users.findMany({
			where: {
				tournamentsId: last_tournament.id,
			},
		});
		return players;
	}

	async lastTournamentGames(): Promise<Games[]> {
		const last_tournament = await this.getLastTournament();
		if (!last_tournament) {
			console.log("lastTournamentPlayers: no valid tournament");
			return [];
		}
		const games: Games[] = await this.prisma.games.findMany({
			where: {
				tournamentsId: last_tournament.id,
			},
		});
		return games;
	}

	async getAlias(id: number): Promise<Alias> {
		const last = await this.getLastTournament();
		const alias = await this.prisma.aliases.findMany({
			where: {
				userId: id,
				tournamentsId: last.id,
			},
		});
		return alias[0];
	}

	async setDone(tournament: Tournaments) {
		await this.prisma.tournaments.update({
			where: {
				id: tournament.id,
			},
			data: {
				status: TStatus.done,
			},
		});
	}

	async getPendingGames(): Promise<PendingGame[]> { //TODO replace logins with alias!!!
		var pendingGames: PendingGame[] = [];
		const last_tournament = await this.getLastTournament();
		if (!last_tournament) {
			console.log("lastTournamentPlayers: no valid tournament");
			return [];
		}
		const players = await this.prisma.users.findMany({
			where: {
				tournamentsId: last_tournament.id,
			},
		});
		for await (const p of players) {
			const games = await this.prisma.games.findMany({
				where: {
					tournamentsId: last_tournament.id,
					OR: [
						{ user1Id: p.id },
						{ user2Id: p.id },
					],
				},
			});
			for (const other of players) {
				for (const g of games) {
					if (p.id !== other.id && other.id !== g.user1Id && other.id !== g.user2Id) {
						const alias1 = await this.getAlias(p.id);
						const alias2 = await this.getAlias(other.id);
						pendingGames.push({
						   	alias1: alias1,
							alias2: alias2,
						});
					}
				}
				if (games.length === 0 && p.id !== other.id) {
					const alias1 = await this.getAlias(p.id);
					const alias2 = await this.getAlias(other.id);
					pendingGames.push({
						alias1: alias1,
						alias2: alias2,
					});
				}
			}
		}
		var uniques: PendingGame[] = [];
		for (const pend of pendingGames) {
			const res = uniques.find((elem) => {
				return (elem.alias1.id === pend.alias2.id && elem.alias2.id === pend.alias1.id);
			});
			if (undefined == res) {
				uniques.push(pend);
			}
		}
		console.log("pendingGames size: ", uniques.length);
		return uniques;
	}

	async isInTournament(id: number): Promise<boolean> {
		const players: Users[] = await this.lastTournamentPlayers();
		var inTournament: boolean = false;
		for (const p of players) {
			if (p.id === id) {
				inTournament = true;
			}
		}
		return (inTournament);
	}

	async joinTournament(id: number, alias: string) {
		const last_tournament = await this.getLastTournament();
		console.log("last_tournament id: ", last_tournament.id);
		const new_alias = await this.prisma.aliases.create({
			data: {
				userId: id,
				alias: alias,
			},
		});
		const res_tourn = await this.prisma.tournaments.update({
			where: {
				id: last_tournament.id,
			},
			data: {
				players: {
					connect: {
						id: id,
					},
				},
				aliases: {
					connect: {
						id: new_alias.id,
					},
				},
			},
		});
		const res_user = await this.prisma.users.update({
			where: {
				id: id,
			},
			data: {
				tournamentsId: last_tournament.id,
			},
		});
	}

	async startTournament() {
		const last_tournament = await this.getLastTournament();
		const res = await this.prisma.tournaments.update({
			where: {
				id: last_tournament.id,
			},
			data: {
				status: TStatus.running,
			},
		});
	}

	async stopTournament() {
		const last_tournament = await this.getLastTournament();
		const res = await this.prisma.tournaments.update({
			where: {
				id: last_tournament.id,
			},
			data: {
				status: TStatus.done,
			},
		});
	}
}
