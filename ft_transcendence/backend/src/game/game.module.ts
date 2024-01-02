import { Module, Global } from '@nestjs/common';  // Import Global
import { GameService } from './game.service';
import { GameController } from './game.controller';
import { GameGateway } from './game.gateway';
import { PrismaService } from 'src/prisma/prisma.service';

@Global()  // Make this module global
@Module({
	imports: [],
  	providers: [GameService, GameGateway, PrismaService], 
  	controllers: [GameController],
 	exports: [GameService, GameGateway],  // Export services and gateways so they can be used globally
})
export class GameModule {}
