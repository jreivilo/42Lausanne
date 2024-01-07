-- CreateTable
CREATE TABLE "Aliases" (
    "id" SERIAL NOT NULL,
    "userId" INTEGER NOT NULL,
    "alias" TEXT NOT NULL,
    "tournamentsId" INTEGER,

    CONSTRAINT "Aliases_pkey" PRIMARY KEY ("id")
);

-- AddForeignKey
ALTER TABLE "Aliases" ADD CONSTRAINT "Aliases_tournamentsId_fkey" FOREIGN KEY ("tournamentsId") REFERENCES "Tournaments"("id") ON DELETE SET NULL ON UPDATE CASCADE;
