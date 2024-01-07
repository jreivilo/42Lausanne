import { Module } from '@nestjs/common';
import { APP_FILTER, APP_INTERCEPTOR } from '@nestjs/core';
import { ConfigModule } from '@nestjs/config';
import { NestExpressApplication } from '@nestjs/platform-express';

import { renderFile } from 'ejs';
import { HttpModule } from '@nestjs/axios'; 
import { AuthModule } from './auth/auth.module';
import { AuthGuard } from './auth/auth.guard';
import { APP_GUARD } from '@nestjs/core';

import { AppController } from './app.controller';
import { AppService } from './app.service';

import { PrismaModule } from './prisma/prisma.module';
import { UsersModule } from './users/users.module';
import { PostsModule } from './posts/posts.module';
import { ChatModule } from './chat/chat.module';

import { GameController } from './game/game.controller';
import { GameModule } from './game/game.module';
import { GameGateway } from './game/game.gateway';
import { TournamentModule } from './tournament/tournament.module';

import base from './config/configuration';
import { ChatGateway } from './chat/chat.gateway';

@Module({
  imports: [ConfigModule.forRoot({
    isGlobal: true,
    load: [base]
  }),
  HttpModule,
  AuthModule,
  PrismaModule,
  UsersModule,
  PostsModule,
  ChatModule,
  GameModule,
  TournamentModule,
],
  controllers: [AppController],
  providers:[
    AppService,
    {
      provide: APP_GUARD,
      useClass: AuthGuard,
    },
  ],
})
export class AppModule {}
