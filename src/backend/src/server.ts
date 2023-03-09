import { fastify } from "fastify";
import { PrismaClient } from "@prisma/client";
import {z} from "zod";

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
            password
        }
    })

    return reply.status(201).send();
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

    await prisma.statistics.create({
        data:{
            UserId,
            ProgramId,
            time
        }
    })
})

// Both ports set to 3333
app.listen({
    port: process.env.PORT ? Number(process.env.PORT) : 3333 
}).then(() => {
    console.log("JA FUNFA")
});
