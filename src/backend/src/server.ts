import { fastify } from "fastify";
import { PrismaClient } from "@prisma/client";
import {z} from "zod";
import {hashPassword, comparePassword} from "./security/passwordHash"
import jwt from "jsonwebtoken";
import { verifyToken } from "./middleware/auth";

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

app.post('/login', async (request, reply) =>{
    const schemaUser = z.object({
        email: z.string().email(),
        password: z.string(),
    })
    try {
                    
        const {email, password} = schemaUser.parse(request.body)



        const user = await prisma.user.findFirstOrThrow({
            where: {
                email
            }
        })

        if(!await comparePassword(password, user.password)){
            return reply.code(400).send({error: "Password incorrect"})
        }
        
        const token = jwt.sign(
            { user_id: user.id, email },
            process.env.TOKEN_KEY,
            {expiresIn: "365d"}
        )

        return reply.status(200).send({token})
    } catch (error) {
        return reply.code(400).send(error)
    }

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
        ProgramName: z.string(),
        time:      z.number()
    })

    try {
        const {UserId, ProgramName, time} = schemaStat.parse(request.body);

        verifyToken(request, reply)

        const { id } = await prisma.program.findUnique({
            select: {
                id: true
            },
            where: {
                ProgramName: ProgramName.toLocaleLowerCase()
            }
        })
        await prisma.statistics.upsert({
            where: {
                UserId_ProgramId: {UserId, ProgramId: id}
            },
            update: {
            time: {
                increment: time,
            },
            },
            create: {
                UserId: UserId,
                ProgramId: id,
                time: time
            },
        })

        return reply.status(201).send();
    } catch (error) {
        return reply.status(400).send({error: "Something went wrong"});
    }
    
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
