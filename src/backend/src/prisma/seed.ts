import { PrismaClient } from '@prisma/client'
import { hashPassword } from '../security/passwordHash'
const prisma = new PrismaClient()
async function main() {
  const moedas = await prisma.user.upsert({
    where: { email: 'moedinhas@gmail.com' },
    update: {},
    create: {
      email: 'moedinhas@gmail.com',
      name: 'Moedinhas',
      password: await hashPassword("moedinhas123"),
      },
    })
  const test = await prisma.user.upsert({
    where: { email: 'testacount@gmail.com' },
    update: {},
    create: {
      email: 'testacount@gmail.com',
      name: 'Test Acount',
      password: await hashPassword("test123"),
      }
  })
  const note = await prisma.program.upsert({
    where: { ProgramName: "onenote" },
    update: {},
    create: {
      ProgramName: 'onenote',
      },
    })
  const excel = await prisma.program.upsert({
    where: { ProgramName: "excel" },
    update: {},
    create: {
      ProgramName: 'excel',
    },
  })
}
main()
  .then(async () => {
    await prisma.$disconnect()
  })
  .catch(async (e) => {
    console.error(e)
    await prisma.$disconnect()
    process.exit(1)
  })