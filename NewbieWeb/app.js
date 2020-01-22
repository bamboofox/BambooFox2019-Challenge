'use strict';

const express = require('express');
const path = require('path');
const morgan = require('morgan');
const helmet = require('helmet');
const fs = require('fs');
const schedule = require('node-schedule');
require('dotenv').config();

const app = express();
const router = express.Router();

app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');

morgan.token('body', (req, res) => {
  return req.method === 'POST' ? JSON.stringify(req.body) : '';
});

app.use(helmet());
app.use(helmet.hidePoweredBy({setTo: 'PHP/7.1.32'}));
app.use(morgan(':remote-addr - :remote-user [:date[clf]] ' +
  '":method :url HTTP/:http-version" :status :res[content-length] :body', {
    stream: fs.createWriteStream('./access.log', {flags: 'a'}),
    intermediate: true,
  }));
app.use(express.json());
app.use(express.urlencoded({extended: false}));
app.use(express.static(__dirname));
app.use(router);

// auto cleanup
const filepath = path.join(__dirname, 'files');
schedule.scheduleJob('0 */1 * * *', () => {
  fs.readdirSync(filepath).forEach((file) => {
    fs.unlinkSync(path.join(filepath, file));
  });
});

router.get('/myfirstweb/index.php', (req, res) => {
  const op = req.query.op || 'new';

  if (op === 'new') {
    res.render('new');
  } else if (op === 'nav') {
    const link = path.normalize(req.query.link || '');
    const filepath = path.join(__dirname, 'nav', link);

    if (!fs.existsSync(filepath) || !fs.lstatSync(filepath).isFile()) {
      res.render('view', {
        error: true,
        content: 'Nav link not found',
      });
    } else {
      const content = fs.readFileSync(filepath);
      const error = content.includes(process.env.FLAG_FORMAT);
      res.render('view', {
        error: error,
        page: 'nav',
        link: link.toUpperCase(),
        content: error ?
          'Found flag format in content, no flag for you!' :
          content,
      });
    }
  } else if (op === 'view') {
    const file = path.normalize(req.query.file || '');
    const filepath = path.join(__dirname, 'files', file);
    let error = false;
    let content = '';

    if (!fs.existsSync(filepath) || !fs.lstatSync(filepath).isFile()) {
      error = true;
      content = 'File not found!';
    } else {
      try {
        content = fs.readFileSync(filepath, 'utf8');
      } catch (err) {
        error = true;
        content = 'Unknown error occurred, please contact the admin!';
      }
    }

    res.render('view', {
      error: error || content.includes(process.env.FLAG_FORMAT),
      page: 'code',
      file: file,
      content: content.includes(process.env.FLAG_FORMAT) ?
        'Found flag format in content, no flag for you!' :
        content,
    });
  } else {
    res.render('view', {
      error: true,
      content: 'Operation not supported!',
    });
  }
});

router.get('/myfirstweb', (req, res) => {
  res.redirect('/myfirstweb/index.php?op=new');
});

router.get('/', (req, res) => {
  res.redirect('/myfirstweb');
});

router.post('/new', (req, res) => {
  const file = req.body.file;
  const code = req.body.code;

  let success = true;
  let message = null;

  if (!(0 <= file.length && file.length <= 16)) {
    success = false;
    message = 'Filename too long';
  } else if (!/^[A-Za-z0-9]+$/.test(file)) {
    success = false;
    message = 'Filename should contain only letters, numbers';
  } else if (!(0 <= code.length && code.length <= 1024)) {
    success = false;
    message = 'Code too long';
  } else if (fs.existsSync(path.join(__dirname, 'files', file))) {
    success = false;
    message = 'File already exists';
  } else {
    try {
      fs.writeFileSync(path.join(__dirname, 'files', file), code,
          {encoding: 'utf8'}, (err) => {
            if (err) throw err;
          });
    } catch (err) {
      success = false;
      message = 'Unknown error occurred, please contact the admin!';
    }
  }

  res.json({
    success: success,
    message: message || '',
  });
});

app.listen(process.env.PORT || 3000);
