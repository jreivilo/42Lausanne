import { Logger, ValidationPipe } from '@nestjs/common';
import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import { SwaggerModule, DocumentBuilder } from '@nestjs/swagger';
import * as cookieParser from 'cookie-parser';
import { AuthGuard } from './auth/auth.guard';

import { join } from 'path';
import * as express from 'express';
import { WsAdapter } from '@nestjs/platform-ws';
import { GameModule } from './game/game.module';
import { GameGateway } from './game/game.gateway';
import { GameController } from './game/game.controller';

async function bootstrap() {
  const app = await NestFactory.create(AppModule);
  app.setGlobalPrefix('api');
  app.useGlobalGuards();
  app.use(cookieParser());
	
  app.useWebSocketAdapter(new WsAdapter(app));
  // app.useGlobalPipes(new ValidationPipe({ whitelist: true }));

  const config = new DocumentBuilder()
    .setTitle('Median')
    .setDescription('The Median API description')
    .setVersion('0.1')
    .build();

  const document = SwaggerModule.createDocument(app, config);
  SwaggerModule.setup('api', app, document);

  app.enableCors({
      methods: 'GET,HEAD,PUT,PATCH,POST,DELETE,OPTIONS',
      // origin: true,
      // origin: 'http://localhost:3000',
      origin: process.env.FRONT_URL || 'http://localhost:3000',
      credentials: true,
    },
  );
  //console.log(process.env);
  await app.listen(process.env.PORT_BACK);
}

bootstrap();
