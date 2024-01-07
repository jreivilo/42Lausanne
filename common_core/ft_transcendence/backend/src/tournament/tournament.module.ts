import { HttpModule } from '@nestjs/axios';
import { Module } from '@nestjs/common';
import { TournamentController } from './tournament.controller';
import { TournamentService } from './tournament.service';
import { TournamentGateway } from './tournament.gateway';
import { PrismaService } from 'src/prisma/prisma.service';
import { JwtModule } from '@nestjs/jwt';
import { JwtAuthGuard } from 'src/auth/guard/jwt.guard';

@Module({
    imports: [HttpModule,
        JwtModule.registerAsync({
          useFactory: async () => ({
            secret: process.env.KEY_JWT,
            signOptions: {
              expiresIn: '1d',
              algorithm: 'HS256'
            }
          })
        })],
	controllers: [TournamentController],
	providers: [TournamentService, TournamentGateway, PrismaService, JwtAuthGuard],
	exports: [TournamentService, TournamentGateway],
})
export class TournamentModule {}
