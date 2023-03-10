import { fastify } from "fastify";
import { PrismaClient } from "@prisma/client";
import {string, z} from "zod";
import {hashPassword, comparePassword} from "./security/passwordHash"

const app = fastify();

const prisma = new PrismaClient();

app.get('/users', async () =>{
    const users = await prisma.user.findMany()

    return {users}
})

app.post('/users', async (request, reply) =>{
    // TODO: ADD confirm password and validate here
    const schemaUser = z.object({
        name: z.string(),
        email: z.string().email(),
        password: z.string(),
    })
    const {name, email, password} = schemaUser.parse(request.body);

    // TODO hash password
    await prisma.user.create({
        data:{
            name,
            email,
            password: await hashPassword(password)
        }
    })

    return reply.status(201).send();
})
// TODO RE-DO this route
app.delete('/users', async (request, reply) =>{
    const schemaStat = z.object({
        id: z.string(),
        email: z.string().email(),
        password: z.string(),
    })
    const {id,email, password} = schemaStat.parse(request.body);

    await prisma.user.delete({
        where: {
            id: id
        }
    })

    return reply.status(202).send();
})

app.get('/programs', async () =>{
    const prog = await prisma.program.findMany();

    return {prog}
})

app.post('/programs', async (request, reply) =>{
    const schemaProgram = z.object({
        ProgramName: z.string()
    })
    const {ProgramName} = schemaProgram.parse(request.body);

    await prisma.program.create({
        data:{
            ProgramName
        }
    })
})

app.get('/statistics', async () =>{
    const stat = await prisma.statistics.findMany();

    return {stat}
})

app.post('/statistics', async (request, reply) =>{
    const schemaStat = z.object({
        UserId: z.string(),
        ProgramId: z.string(),
        time:      z.number()
    })
    const {UserId, ProgramId, time} = schemaStat.parse(request.body);

    await prisma.statistics.upsert({
        where: {
            UserId_ProgramId: {UserId, ProgramId}
        },
        update: {
          time: {
            increment: time,
          },
        },
        create: {
          UserId: UserId,
          ProgramId: ProgramId,
          time: time
        },
    })

    return reply.status(201).send();
})

app.delete('/statistics', async (request, reply) =>{
    const schemaStat = z.object({
        UserId: z.string(),
        ProgramId: z.string(),
    })
    const {UserId, ProgramId} = schemaStat.parse(request.body);

    await prisma.statistics.delete({
        where: {
            UserId_ProgramId: {UserId, ProgramId}
        }
    })

    return reply.status(202).send();
})
// Both ports set to 3333
app.listen({
    port: process.env.PORT ? Number(process.env.PORT) : 3333 
}).then(() => {
    console.log("JA FUNFA")
});
