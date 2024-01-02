import { Injectable, NotFoundException } from '@nestjs/common'
import { WebSocketServer } from '@nestjs/websockets';
import { PrismaService } from 'src/prisma/prisma.service';
import { UsersService } from 'src/users/users.service';
import { ChatDto, PostDto } from './dto/create-chat.dto';
import { UpdateChatDto } from './dto/update-chat.dto';
import { HttpService } from '@nestjs/axios';
import { Chatrooms, Posts } from '@prisma/client';
import { identity } from 'rxjs';
import { MessageDto } from './chat.gateway';


@Injectable()
export class ChatService {
  constructor(private prisma: PrismaService, private httpService: HttpService) { }

  async createChatRoom(room: ChatDto): Promise<Chatrooms> {
    console.log('creation chatroom id in function', room.user1Id, room.user2Id);
    console.log("find user 2 before");
    const user2 = await this.prisma.users.findUnique({ where: { id: room.user2Id }, });
    console.log("find user 2 after");

    if (!user2) {
      throw new NotFoundException(`User with id ${room.user2Id} not found.`)
    }

    const chatroom = await this.prisma.chatrooms.create({
      data: {
        user1Id: room.user1Id,
        user2Id: room.user2Id,
        posts: {
          create: [
            {
              text: room.posts[0].text,
              authorId: room.user1Id,
            },
          ],
        },
      },
      include: {
        posts: true,
      },
    });
    console.log("Message therorique de la room : ", room.posts[0].text);
    console.log('Chatroom created:', chatroom);

    return chatroom;
  }


  async deleteChat(id: number): Promise<void> {
    console.log("delet chatroom in service : ", id);

    const chatroom = await this.prisma.chatrooms.findUnique({ where: { id: id } })
    console.log('efface chatroom backend', chatroom);

    if (!chatroom) {
      throw new NotFoundException('Chatroom with Id ${id} not found');
    }

    await this.prisma.chatrooms.delete({
      where: { id: id },
    });

    return;
  }

  async getChatroomMessages(chatRoomId: number): Promise<PostDto[]> {
    const chatroom = await this.findById(chatRoomId);

    if (!chatroom) {
      throw new NotFoundException(`Chatroom with ID ${chatRoomId} not found.`);
    }

    const messages = await this.prisma.posts.findMany({
      where: {
        chatroomId: chatroom.id,
      },
    });

    return messages.map((message) => ({
      text: message.text,
      authorId: message.authorId,
      chatRoomId: message.chatroomId,
    }));


  }

  async saveMessage(data: MessageDto): Promise<Posts | null> {
    if (data.text.length > 250)
    {
      console.log ("message to long :",data.text.length);
      return ;
    }
    const chatroom = await this.findById(data.chatroomId);
    const condition = data.authorId === chatroom.user1Id ? chatroom.user1Block : chatroom.user2Block;
    if (condition) {
      return null;
    }
    const message = await this.prisma.posts.create({
      data: {
        text: data.text,
        authorId: data.authorId,
        chatroomId: data.chatroomId,
      },
    });
    console.log("Data dans saveMessage", data);
    return message;
  }

  // async sendMessage(data: MessageDto): Promise<Posts> {
    // const message = await this.saveMessage(data);
// 
    // return message;
  // }

  async receivedMessage(message: string): Promise<string> {
    return message;
  }

  async findAllRoom() {
    return this.prisma.chatrooms.findMany({
      include: {
        user1: true,
        user2: true,
      },
    });
  }

  async findById(id: number) {
    console.log("find by id is used ");
    return this.prisma.chatrooms.findUnique({ where: { id: id }, include: { posts: true } });
  }

  async blockUsers(data: { meId: number, infoUser1: any, chatId: number }) {
    let updateBlockedUser;
    if (data.meId === data.infoUser1.id) {
      updateBlockedUser = await this.prisma.chatrooms.update({
        where: { id: data.chatId },
        data: {
          user2Block: true,
        },
      });
      console.log("invited blocked")
    }
    else {
      updateBlockedUser = await this.prisma.chatrooms.update({
        where: { id: data.chatId },
        data: {
          user1Block: true,
        },
      });
      console.log("owner blocked")
    }
    return updateBlockedUser;
  }

  async unBlockUsers(data : {meId: number, infoUser1: any, chatId: number}) {
    let updateUnBlockedUser;
    if (data.meId === data.infoUser1.id) {
      updateUnBlockedUser = await this.prisma.chatrooms.update({
        where: { id: data.chatId },
        data: {
          user2Block: false,
        },
      });
      console.log("invited unblocked")
    }
    else {
      updateUnBlockedUser = await this.prisma.chatrooms.update({
        where: { id: data.chatId },
        data: {
          user1Block: false,
        },
      });
      console.log("owner unblocked")
    }
    return updateUnBlockedUser;
  }
}