-- AlterTable
ALTER TABLE "Chatrooms" ADD COLUMN     "user1Block" BOOLEAN NOT NULL DEFAULT false,
ADD COLUMN     "user2Block" BOOLEAN NOT NULL DEFAULT false;
