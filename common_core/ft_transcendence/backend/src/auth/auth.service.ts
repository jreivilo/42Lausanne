import {HttpException, HttpStatus, Injectable} from '@nestjs/common';
import {HttpService} from '@nestjs/axios';
import {ConfigService} from '@nestjs/config';
import {createCipheriv, createDecipheriv, randomBytes} from 'crypto';
import {CreateUserDto} from 'src/auth/dto/create-user.dto';
import {PrismaService} from 'src/prisma/prisma.service';
import {JwtService} from '@nestjs/jwt';
import {authenticator} from 'otplib';
import {response} from 'express';

@Injectable()
export class AuthService {
    [x: string]: any;

    private CLIENT_ID: string;
    private CLIENT_SECRET: string;
    private REDIRECT_URI: string;


    constructor(
        private httpService: HttpService,
        private configService: ConfigService,
        private prisma: PrismaService,
        private jwtService: JwtService
    ) {
        this.CLIENT_ID = this.configService.get<string>('client.id');
        this.CLIENT_SECRET = this.configService.get<string>('client.secret');
        this.REDIRECT_URI = this.configService.get<string>('client.uri');
    }

    async exchangeCodeForToken(code: string): Promise<any> {
        try {
            const response = await this.httpService.post('https://api.intra.42.fr/oauth/token', {
                grant_type: 'authorization_code',
                client_id: this.CLIENT_ID,
                client_secret: this.CLIENT_SECRET,
                code: code,
                redirect_uri: this.REDIRECT_URI,
            }).toPromise();
            return response.data;
        } catch (error) {
            console.log(response.statusCode);
            throw new HttpException('Failed to exchange code for token', HttpStatus.BAD_REQUEST);
        }
    }

    async getJwtToken(id: number, twofactor: string): Promise<any> {
        if (twofactor == "false") {
            twofactor = "none";
        } else if (twofactor == "valid") {
            twofactor = "valid";
        } else {
            twofactor = "need";
        }
        const payload = {id: id, twofactor: twofactor};
        const jwt_token = this.jwtService.sign(payload);
        return jwt_token;
    }

    async generateQRCode(userID: number): Promise<any> {
        const user = await this.prisma.users.findUnique({where: {id: userID}, select: {username: true}});
        const secret = authenticator.generateSecret();
        const otpauth = authenticator.keyuri(user.username, 'Pong', secret);
        await this.prisma.users.update({where: {id: userID}, data: {hash2FA: secret}});
        return otpauth;
    }

    async verify2FA(userID: number, code: string): Promise<boolean> {
        const user = await this.prisma.users.findUnique({where: {id: userID}, select: {hash2FA: true}});
        return authenticator.verify({
            token: code,
            secret: user.hash2FA
        });
    }

    async checkTokenValidity(token: string): Promise<string> {
        try {
            const decoded = this.jwtService.decode(token);

            if (decoded['twofactor'] === "none" || decoded['twofactor'] === "valid") {
                return 'valid';
            } else if (decoded['twofactor'] === "need") {
                return 'need';
            } else {
                return 'invalid';
            }
        } catch (error) {
            console.error(error);
            return 'invalid';
        }
    }

    async enable2FA(userID: number) {
        const user = await this.prisma.users.findUnique({where: {id: userID}});

        await this.prisma.users.update({
            where: {id: userID}, data: {
                twofactor: true
            }
        });
    }

    async disable2FA(userID: number) {
        const user = await this.prisma.users.findUnique({where: {id: userID}});
        await this.prisma.users.update({
            where: {id: userID}, data: {
                twofactor: false,
                hash2FA: null,
            }
        });
    }

    async getMeInfo(accessToken: string): Promise<any> {
        try {
            const response = await this.httpService.get('https://api.intra.42.fr/v2/me', {
                headers: {Authorization: `Bearer ${accessToken}`},
            }).toPromise();
            return response.data;
        } catch (error) {
            throw new HttpException('Failed to fetch user info', HttpStatus.BAD_REQUEST);
        }
    }

    async fetchUserByLogin(login: string): Promise<any> {
        return this.prisma.users.findUnique({where: {login}});
    }

    async createUser(user: any): Promise<any> {
        this.createUserDto = new CreateUserDto();
        this.createUserDto.login = user.login;
        this.createUserDto.username = user.login;
        this.createUserDto.avatar = user.image.versions.medium;
        return this.prisma.users.create({data: this.createUserDto});
    }

    getClientId() {
        return this.CLIENT_ID;
    }

    getRedirectUri() {
        return this.REDIRECT_URI;
    }

    async findMe(id: number) {
        return this.prisma.users.findUnique({where: {id}});
    }
}
