/*
  Warnings:

  - You are about to drop the column `participants` on the `Chatrooms` table. All the data in the column will be lost.
  - You are about to drop the column `password` on the `Users` table. All the data in the column will be lost.

*/
-- CreateEnum
CREATE TYPE "dmStatus" AS ENUM ('pending', 'accepted', 'blocked');

-- CreateEnum
CREATE TYPE "role" AS ENUM ('owner', 'admin', 'user');

-- AlterEnum
ALTER TYPE "ChatroomStatus" ADD VALUE 'protected';

-- AlterTable
ALTER TABLE "Chatrooms" DROP COLUMN "participants",
ADD COLUMN     "password" TEXT,
ALTER COLUMN "status" SET DEFAULT 'public';

-- AlterTable
ALTER TABLE "Users" DROP COLUMN "password";

-- CreateTable
CREATE TABLE "Members" (
    "id" SERIAL NOT NULL,
    "userId" INTEGER NOT NULL,
    "chatroomId" INTEGER NOT NULL,
    "role" "role" NOT NULL DEFAULT 'user',
    "create_at" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "update_at" TIMESTAMP(3) NOT NULL,
    "delete_at" TIMESTAMP(3),

    CONSTRAINT "Members_pkey" PRIMARY KEY ("id")
);

-- AddForeignKey
ALTER TABLE "Members" ADD CONSTRAINT "Members_userId_fkey" FOREIGN KEY ("userId") REFERENCES "Users"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "Members" ADD CONSTRAINT "Members_chatroomId_fkey" FOREIGN KEY ("chatroomId") REFERENCES "Chatrooms"("id") ON DELETE RESTRICT ON UPDATE CASCADE;
