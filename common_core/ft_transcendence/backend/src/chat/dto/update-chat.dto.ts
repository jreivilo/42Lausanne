import { PartialType } from '@nestjs/swagger';
import { ChatDto } from './create-chat.dto';

export class UpdateChatDto extends PartialType(ChatDto) {}
