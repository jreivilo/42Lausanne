
import { Controller, Get, UseGuards, Req, Param, Post, Body, Delete, Request } from '@nestjs/common';
import { ChatService } from './chat.service';
import { ChatDto } from './dto/create-chat.dto';
import { JwtAuthGuard } from 'src/auth/guard/jwt.guard';

@Controller('chat')
export class ChatController {
  constructor(private readonly chatService: ChatService) {}

@Post()
@UseGuards(JwtAuthGuard)
async createChatRoom(@Request() req, @Body() resp: ChatDto ) {
  console.log("===============================================");
  console.log(resp);
  console.log('creation chatroom id');
  console.log('Data received from frontend:', resp);
  return this.chatService.createChatRoom(resp);
}

@Get()
@UseGuards(JwtAuthGuard)
findAll() {
  console.log('Route findAllRooms is called');
  return this.chatService.findAllRoom();
}

@Get(':id')
@UseGuards(JwtAuthGuard)
async findById(@Param('id') id: string) {
  const numId = parseInt(id, 10);
  return this.chatService.findById(numId);
}

@Delete(':id')
@UseGuards(JwtAuthGuard)
deleteChat(@Param('id') id: string) {
  console.log('clear chatroom backend', id);
  const numId = parseInt(id, 10);
  //console.log(numId);
  return this.chatService.deleteChat(numId);
}

@Get('/getMessages/:id')
@UseGuards(JwtAuthGuard)
async getMessages(@Param('id') id:string) {
  console.log("dans le getmessage", id);
  const chatroomId = parseInt(id, 10);
  const chatRoomMessages = await this.chatService.getChatroomMessages(chatroomId);
  return(chatRoomMessages);
}
/*
@Post(':chatId/add-member/:userId')
@UseGuards(JwtAuthGuard)
async addMember(@Param('ChatId') chatroomId: string, @Param('userId') userId: string) {
  const numChatroomId = parseInt(chatroomId, 10);
  const numUserId = parseInt(userId, 10);
  return this.chatService.addMember(numChatroomId, numUserId);
}
*/
/*
@Get(':id/details')
@UseGuards(JwtAuthGuard)
async getChatroomDetails(@Param('id') id: string) {
  const numId = parseInt(id, 10);
  const chatroom = await this.chatService.getChatroomDetails(numId);
  return {
    owner: chatroom.members.find(member => member.role === 'owner')?.user.username || '',
    members: chatroom.members.map(member => member.user.username),
  };
}
*/
}