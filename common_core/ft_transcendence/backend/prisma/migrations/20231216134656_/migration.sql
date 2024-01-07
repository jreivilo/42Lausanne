/*
  Warnings:

  - Added the required column `user1Score` to the `Games` table without a default value. This is not possible if the table is not empty.
  - Added the required column `user2Score` to the `Games` table without a default value. This is not possible if the table is not empty.

*/
-- CreateEnum
CREATE TYPE "TStatus" AS ENUM ('not_started', 'running', 'done');

-- AlterTable
ALTER TABLE "Games" ADD COLUMN     "tournamentsId" INTEGER,
ADD COLUMN     "user1Score" INTEGER NOT NULL,
ADD COLUMN     "user2Score" INTEGER NOT NULL;

-- AlterTable
ALTER TABLE "Users" ADD COLUMN     "tournamentsId" INTEGER;

-- CreateTable
CREATE TABLE "Tournaments" (
    "id" SERIAL NOT NULL,
    "status" "TStatus" NOT NULL,
    "create_at" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "update_at" TIMESTAMP(3) NOT NULL,
    "delete_at" TIMESTAMP(3),

    CONSTRAINT "Tournaments_pkey" PRIMARY KEY ("id")
);

-- AddForeignKey
ALTER TABLE "Users" ADD CONSTRAINT "Users_tournamentsId_fkey" FOREIGN KEY ("tournamentsId") REFERENCES "Tournaments"("id") ON DELETE SET NULL ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "Games" ADD CONSTRAINT "Games_tournamentsId_fkey" FOREIGN KEY ("tournamentsId") REFERENCES "Tournaments"("id") ON DELETE SET NULL ON UPDATE CASCADE;
