import { Injectable, HttpException, HttpStatus } from '@nestjs/common';
import { CreateUserDto } from '../auth/dto/create-user.dto';
import { UpdateUserDto } from './dto/update-user.dto';
import { PrismaService } from 'src/prisma/prisma.service';
import { HttpService } from '@nestjs/axios';

@Injectable()
export class UsersService {
  constructor (private prisma: PrismaService, private httpService: HttpService) {}

  async create(createUserDto: CreateUserDto): Promise<any> {
    return this.prisma.users.create({ data: createUserDto });
  }

  async findAll() {
    return this.prisma.users.findMany();
  }

  async findMe(id: number) {
    return this.prisma.users.findUnique({ where: { id } });
  }

  async findOneByLogin(login: string) {
    return this.prisma.users.findUnique({ where: { login } });
  }

  async findOneByID(id: number) {
    return this.prisma.users.findUnique({ where: { id } });
  }

  async update(id: number, updateUserDto: UpdateUserDto) {
    return this.prisma.users.update({ where: { id }, data: updateUserDto });
  }

  async remove(id: number) {
    return `This action removes a #${id} user`;
  }

  async getStats(id: number) {
    const games = await this.prisma.games.findMany({ where: { OR: [{ user1Id: id }, { user2Id: id }] } });
    if (!games) {
      return { win: 0, lost: 0 };
    }
    const win = games.filter(game =>
        (game.user1Id === id && game.user1Score > game.user2Score) ||
        (game.user2Id === id && game.user2Score > game.user1Score)).length;
    const lost = games.filter(game =>
        (game.user1Id === id && game.user1Score < game.user2Score) ||
        (game.user2Id === id && game.user2Score < game.user1Score)).length;

    return { win, lost };
  }
}

