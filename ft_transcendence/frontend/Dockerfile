FROM node:20.6

WORKDIR /app

COPY package*.json ./
RUN npm install
RUN npm install -g react

COPY . .
RUN npm run build

EXPOSE 3000
CMD ["npm", "run", "start"]