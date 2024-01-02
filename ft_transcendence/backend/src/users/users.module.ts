import { Module, forwardRef } from '@nestjs/common';
import { UsersService } from './users.service';
import { UsersController } from './users.controller';
import { AuthModule } from 'src/auth/auth.module';
import { PrismaModule } from 'src/prisma/prisma.module';
import { PrismaService } from 'src/prisma/prisma.service';
import { HttpModule } from '@nestjs/axios';
import { AuthGuard } from 'src/auth/auth.guard';
import { JwtModule } from '@nestjs/jwt';
import { JwtAuthGuard } from 'src/auth/guard/jwt.guard';

@Module({
  controllers: [UsersController],
  providers: [UsersService, PrismaService, AuthGuard, JwtAuthGuard],
  imports: [HttpModule, PrismaModule, AuthModule,
    JwtModule.registerAsync({
      useFactory: async () => ({
        secret: process.env.KEY_JWT,
        signOptions: {
          expiresIn: '1d',
          algorithm: 'HS256'
        }
      })
    })],
  exports: [UsersService]
})
export class UsersModule {}
