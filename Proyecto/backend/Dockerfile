FROM node:latest


WORKDIR /usr/src/app

COPY . .

RUN npm install
# If you are building your code for production
# RUN npm ci --only=production

EXPOSE 5000
CMD [ "npm", "start" ]