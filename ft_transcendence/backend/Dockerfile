FROM node:20.6

WORKDIR /app
COPY package*.json ./
RUN npm install

COPY . .
RUN npx prisma generate
#RUN npx prisma migrate deploy
RUN npm run build
RUN chmod +x entry_point.sh

EXPOSE 3001
CMD ["./entry_point.sh"]
