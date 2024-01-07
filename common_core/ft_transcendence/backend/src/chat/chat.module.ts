import { HttpModule } from '@nestjs/axios';
import { Module, Global } from '@nestjs/common';  // Import Global
import { ChatGateway } from './chat.gateway';
import { ChatController } from './chat.controller';
import { ChatService } from './chat.service';
import { PrismaService } from 'src/prisma/prisma.service';
import { JwtModule } from '@nestjs/jwt';
import { JwtAuthGuard } from 'src/auth/guard/jwt.guard';

@Global()
@Module( {
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
    controllers: [ChatController],
    providers: [ChatService, ChatGateway, PrismaService, JwtAuthGuard],
    exports: [ChatService, ChatGateway],
})

export class ChatModule {}