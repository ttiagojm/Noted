import { FastifyReply, FastifyRequest } from "fastify";
import jwt from "jsonwebtoken"

export function verifyToken(req: FastifyRequest, reply: FastifyReply){
    const token = req.headers.authorization?.split(" ");
    if(!token){
        return reply.status(403).send({error: "A token is required for authentication"})
    }
    try {
        jwt.verify(token[1], process.env.TOKEN_KEY);
    } catch (err) {
        return reply.status(401).send("Invalid Token");
    }
}