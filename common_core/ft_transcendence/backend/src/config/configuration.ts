import { ConfigFactory } from '@nestjs/config';

const configuration: ConfigFactory = () => ({
  client: {
    id: process.env.CLIENT_ID,
    secret: process.env.CLIENT_SECRET,
    uri: process.env.REDIRECT_URI,
},
});

export default configuration;