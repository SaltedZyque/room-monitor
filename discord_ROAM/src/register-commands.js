require('dotenv').config();
const { REST, Routes, ApplicationCommandOptionType } = require('discord.js');

const commands = [
    {
        name:'hey',
        description:'replies with an important message'
    },
    {
        name:'ping',
        description:'ping check'
    },
    {
        name:'add',
        description:'adds two numbers',
        options: [
            {
                name: 'firstnum',
                description: 'first number...',
                type: ApplicationCommandOptionType.Number,
                choices: [
                    {
                        name:'one',
                        value: 1,
                    },
                    {
                        name:'two',
                        value: 2,
                    },
                    {
                        name:'three',
                        value: 3,
                    },
                ],
                required: true,
            },
            {
                name: 'secnum',
                description: 'second number...',
                type: ApplicationCommandOptionType.Number,
                required: true,
            },
        ]
    }
];

const rest = new REST({version:'10'}).setToken(process.env.TOKEN);

(async() =>  {
    try {
        console.log('Registering slash comms')

        await rest.put(
            Routes.applicationGuildCommands(process.env.CLIENT_ID, process.env.GUILD_ID),
            { body: commands }
        );

        console.log('Registered slash comms');
    } catch (error) {
        console.log(`Error detected: ${error}`);
    }
})();