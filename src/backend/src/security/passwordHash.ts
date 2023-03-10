import bcrypt from "bcrypt";

const salts = Number(process.env.SALT);

export async function hashPassword(plaintextPassword: string) {
    const hash = await bcrypt.hash(plaintextPassword, salts);
    return hash;
}
    // compare password
export async function comparePassword(plaintextPassword: string, hash: string) {
    const result = await bcrypt.compare(plaintextPassword, hash);
    return result;
}