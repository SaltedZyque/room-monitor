const { ApplicationCommandOptionType, PermissionFlagsBits} = require('discord.js');

module.exports = {
    name: "ban",
    description: "ban a member",
    // devOnly: Boolean
    // testOnly: Boolean
    options: [
        {
            name: 'target-user',
            description: 'big bans',
            required: true,
            type: ApplicationCommandOptionType.Mentionable,
        },
        {
            name: 'reason',
            description: 'why naughty',
            type: ApplicationCommandOptionType.String,
        }
    ],
    permissionsRequired: [PermissionFlagsBits.Administrator],
    botPermissions: [PermissionFlagsBits.Administrator],

    callback: (client, interaction) => {
        interaction.reply(`get banned`);
    },
}; 