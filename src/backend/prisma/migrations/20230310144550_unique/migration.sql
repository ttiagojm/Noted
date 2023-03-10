/*
  Warnings:

  - A unique constraint covering the columns `[UserId,ProgramId]` on the table `Statistics` will be added. If there are existing duplicate values, this will fail.

*/
-- CreateIndex
CREATE UNIQUE INDEX "Statistics_UserId_ProgramId_key" ON "Statistics"("UserId", "ProgramId");
