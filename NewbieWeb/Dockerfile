FROM node:latest

WORKDIR /usr/src/app

COPY package*.json ./

RUN npm i && mkdir files

COPY . .

EXPOSE 30000

CMD ["node", "app.js"]
