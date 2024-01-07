import {
    MessageBody,
    WebSocketGateway,
    WebSocketServer,
    SubscribeMessage,
    OnGatewayConnection,
    OnGatewayDisconnect,
    ConnectedSocket,
} from '@nestjs/websockets';

import { Server } from 'ws'
import { Inject } from '@nestjs/common';
import { ChatService } from './chat.service';

export class MessageDto {
    text: string;
    authorId: number;
    receiverId: number;
    chatroomId: number;
};

@WebSocketGateway({
    cors: {
        origin: '*',
        credentials: true,
    },
    path: '/api',
})
export class ChatGateway implements OnGatewayConnection, OnGatewayDisconnect {
    @WebSocketServer()
    server: Server;
    clients: any[];

    constructor(@Inject(ChatService) private readonly chatService: ChatService) {
		this.clients = [];
	}

    handleConnection(@ConnectedSocket() client: any) {
        console.log('Chat Gateway Client connected.');
        this.clients.push(client);
        client.send(JSON.stringify({ events: 'refresh', data: {} }));
    }

    handleDisconnect(@ConnectedSocket() client: any) {
        console.log('Chat Gateway Client disconnected.');
        this.clients = this.clients.filter((elem) => elem !== client);
    }

    @SubscribeMessage('registerNewClient')
    async registerNewClient(@ConnectedSocket() client: any, @MessageBody() id: number ) {
        console.log("register new client");
        console.log(id);
        this.clients[id] = client;
        console.log("registerd id: ", id);
    }

    @SubscribeMessage('newMessage')
    async newMessage(@ConnectedSocket() client: any, @MessageBody() data: MessageDto) {
        console.log("message reveived in chat!");
        console.log(data.text);
        console.log("Subscribe message", data);
		this.clients[data.authorId] = client;
		console.log("registerd id: ", data.authorId);

        const savedMessage = await this.chatService.saveMessage(data);
        if (savedMessage !== null) {
            this.clients.forEach((c) => {
                c.send(JSON.stringify({ events: 'refresh', data: {} }));
                console.log("event refresh");
            });
            console.log("message envoyee au client de la chatroom", savedMessage);
        } else {
            console.log("message not sent, author is blocked");
        };
    }

    @SubscribeMessage('GetMessages')
    async displayMessage(@ConnectedSocket() client: any, @MessageBody() chatId: number) {

        const AllMessages = await this.chatService.getChatroomMessages(chatId);
        console.log("ChatId number :", chatId);
        console.log("display all messages : ", AllMessages);
        return ({ events: 'GetMessages', data: AllMessages });
    }

    @SubscribeMessage("blockUsers")
    async blockUsers(@ConnectedSocket() client: any, @MessageBody() data: { meId: number, infoUser1: any, chatId: number }) {
        const userBlocked = await this.chatService.blockUsers(data);
        console.log("inside blocked gateway");
        console.log("userBlocked", userBlocked);
        this.clients.forEach((c) => {
            c.send(JSON.stringify({ events: 'refresh', data: {} }));
            console.log("event refresh");
        });
        // return ({events: 'AlertUserBlock', data : userBlocked});
    }

    @SubscribeMessage("unBlockUsers")
    async unblockUsers(@ConnectedSocket() client: any, @MessageBody() data: { meId: number, infoUser1: any, chatId: number }) {
        const unBlockedUser = await this.chatService.unBlockUsers(data);
        console.log("unblocked users");
        console.log("userBlocked", unBlockedUser);
        this.clients.forEach((c) => {
            c.send(JSON.stringify({ events: 'refresh', data: {} }));
            console.log("event refresh");
        });
    }

    @SubscribeMessage("inviteGameFromChat")
    async inviteGame(@ConnectedSocket() client: any, @MessageBody() data: { meId : number, otherId : number, chatId: number }) {
        console.log("invite game from gateway");
        console.log("moi : %d, et l'invite : %d et la chatroom: %d", data.meId, data.otherId, data.chatId);
		if (this.clients[data.otherId]) {
			this.clients[data.otherId].send(JSON.stringify({ events: 'inviteGameFromChat', data: data}));
		} else {
			console.log("client not registered");
		}
    }
}
