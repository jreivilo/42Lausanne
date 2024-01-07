import { PrismaClient } from '@prisma/client';

const prisma = new PrismaClient();

async function main() {
    const bella = await prisma.users.upsert({
        where: { username: 'Bella' },
        update: {},
        create: {
            login: 'Bella_Cat',
            username: 'Bella',
            avatar: 'https://cataas.com/cat'
        },
    });

    const bob = await prisma.users.upsert({
        where: { username: 'Bob' },
        update: {},
        create: {
            login: 'BobCat',
            username: 'Bob',
            avatar: 'https://cataas.com/cat'
        },
    });
    
    const kitty = await prisma.users.upsert({
        where: { username: 'Kitty' },
        update: {},
        create: {
            login: 'KittyCat',
            username: 'Kitty',
            avatar: 'https://cataas.com/cat'
        },
    });
    const tiger = await prisma.users.upsert({
        where: { username: 'Tiger' },
        update: {},
        create: {
            login: 'TigerCat',
            username: 'Tiger',
            avatar: 'https://cataas.com/cat'
        },
    });

  console.log({ bella, bob, kitty, tiger });
}

main()
  .catch((e) => {
    console.error(e);
    process.exit(1);
  })
  .finally(async () => {
    await prisma.$disconnect();
  });

