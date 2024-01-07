/*
  Warnings:

  - You are about to drop the column `ownerId` on the `Chatrooms` table. All the data in the column will be lost.

*/
-- DropForeignKey
ALTER TABLE "Chatrooms" DROP CONSTRAINT "Chatrooms_ownerId_fkey";

-- AlterTable
ALTER TABLE "Chatrooms" DROP COLUMN "ownerId";
