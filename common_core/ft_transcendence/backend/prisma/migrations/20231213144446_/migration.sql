-- DropForeignKey
ALTER TABLE "Posts" DROP CONSTRAINT "Posts_chatroomId_fkey";

-- AddForeignKey
ALTER TABLE "Posts" ADD CONSTRAINT "Posts_chatroomId_fkey" FOREIGN KEY ("chatroomId") REFERENCES "Chatrooms"("id") ON DELETE CASCADE ON UPDATE CASCADE;
