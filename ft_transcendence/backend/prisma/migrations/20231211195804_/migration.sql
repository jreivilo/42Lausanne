/*
  Warnings:

  - You are about to drop the column `password` on the `Chatrooms` table. All the data in the column will be lost.
  - You are about to drop the column `status` on the `Chatrooms` table. All the data in the column will be lost.
  - You are about to drop the column `title` on the `Chatrooms` table. All the data in the column will be lost.
  - You are about to drop the column `published` on the `Posts` table. All the data in the column will be lost.
  - You are about to drop the `Members` table. If the table is not empty, all the data it contains will be lost.
  - Added the required column `user1Id` to the `Chatrooms` table without a default value. This is not possible if the table is not empty.
  - Added the required column `user2Id` to the `Chatrooms` table without a default value. This is not possible if the table is not empty.

*/
-- DropForeignKey
ALTER TABLE "Members" DROP CONSTRAINT "Members_chatroomId_fkey";

-- DropForeignKey
ALTER TABLE "Members" DROP CONSTRAINT "Members_userId_fkey";

-- AlterTable
ALTER TABLE "Chatrooms" DROP COLUMN "password",
DROP COLUMN "status",
DROP COLUMN "title",
ADD COLUMN     "user1Id" INTEGER NOT NULL,
ADD COLUMN     "user2Id" INTEGER NOT NULL;

-- AlterTable
ALTER TABLE "Posts" DROP COLUMN "published";

-- DropTable
DROP TABLE "Members";

-- DropEnum
DROP TYPE "ChatroomStatus";

-- DropEnum
DROP TYPE "role";

-- CreateTable
CREATE TABLE "Games" (
    "id" SERIAL NOT NULL,
    "user1Id" INTEGER NOT NULL,
    "user2Id" INTEGER NOT NULL,
    "create_at" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "update_at" TIMESTAMP(3) NOT NULL,
    "delete_at" TIMESTAMP(3),

    CONSTRAINT "Games_pkey" PRIMARY KEY ("id")
);

-- AddForeignKey
ALTER TABLE "Chatrooms" ADD CONSTRAINT "Chatrooms_user1Id_fkey" FOREIGN KEY ("user1Id") REFERENCES "Users"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "Chatrooms" ADD CONSTRAINT "Chatrooms_user2Id_fkey" FOREIGN KEY ("user2Id") REFERENCES "Users"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "Games" ADD CONSTRAINT "Games_user1Id_fkey" FOREIGN KEY ("user1Id") REFERENCES "Users"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "Games" ADD CONSTRAINT "Games_user2Id_fkey" FOREIGN KEY ("user2Id") REFERENCES "Users"("id") ON DELETE RESTRICT ON UPDATE CASCADE;
