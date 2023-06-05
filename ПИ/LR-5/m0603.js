const nodemailer = require('nodemailer');

const sender = 'navvallny@yandex.by';
const receiver = 'ilya33223@gmail.com';
const password = 'r_M5UgV3::jQa6S';


const transporter = nodemailer.createTransport({
    host: 'smtp.yandex.com',
    port: 465,
    secure: false,
    service: 'Yandex',
    auth: {
        user: sender,
        pass: password
    }
});


send = (message) =>
{

    const mailOptions = {
        from: sender,
        to: receiver,
        subject: 'О евангел',
        text: message
    }

    transporter.sendMail(mailOptions, (err, info) => {
        err ? console.log(err) : console.log('Sent: ' + info.response);
    })
}

module.exports = send;