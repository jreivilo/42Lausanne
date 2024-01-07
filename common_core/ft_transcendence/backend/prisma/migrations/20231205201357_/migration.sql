/*
  Warnings:

  - A unique constraint covering the columns `[login]` on the table `Users` will be added. If there are existing duplicate values, this will fail.
  - Added the required column `login` to the `Users` table without a default value. This is not possible if the table is not empty.

*/
-- AlterTable
ALTER TABLE "Users" ADD COLUMN     "hash2FA" TEXT,
ADD COLUMN     "login" TEXT NOT NULL,
ADD COLUMN     "twofactor" BOOLEAN NOT NULL DEFAULT false;

-- CreateIndex
CREATE UNIQUE INDEX "Users_login_key" ON "Users"("login");
