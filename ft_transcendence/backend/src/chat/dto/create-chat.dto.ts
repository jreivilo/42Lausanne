import { Posts, Users } from "@prisma/client";

export class ChatDto {
    id: number;
    user1Id: number;
    user2Id: number;
    user1: Users;
    user2: Users;
    posts: PostDto[];
}

export class PostDto {
    text : string;
    authorId : number;
    chatRoomId: number;
}