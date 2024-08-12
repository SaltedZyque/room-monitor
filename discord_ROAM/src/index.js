require('dotenv').config(); // access the password env file
const { Client, IntentsBitField} = require('discord.js');
const eventHandler = require('./handlers/eventHandler');

const client = new Client({
    intents: [
        IntentsBitField.Flags.Guilds,
        IntentsBitField.Flags.GuildMembers,
        IntentsBitField.Flags.GuildMessages,
        IntentsBitField.Flags.MessageContent,
    ]
});

/* 
client.on('ready', (c) => {
    console.log(`🤖 ${c.user.tag} is online`);
}) // event listener checks if bot is ready

client.on('interactionCreate', (interaction) => {
    if (!interaction.isChatInputCommand()) return;

    if (interaction.commandName === 'hey') {
        interaction.reply('hiiiiiii');
    }

    if (interaction.commandName === 'ping') {
        interaction.reply('pong');
    }

    if (interaction.commandName === 'add') {
        const num1 = interaction.options.get('firstnum')?.value;
        const num2 = interaction.options.get('secnum')?.value;

        interaction.reply(`Sum = ${num1 + num2}, I love doing Maths for ${interaction.user.displayName}!`);
    }

    // console.log(interaction.commandName);
})


client.on('messageCreate', (msg) => {
    if (msg.author.bot) {return;}
    if (msg.content === 'test'){
        msg.reply('ping!')
    }; 
}) 
    */

eventHandler(client);

client.login(
    process.env.TOKEN
); // token accessed from private env