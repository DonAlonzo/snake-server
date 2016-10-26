var execFile = require('child_process').execFile;
var githubhook = require('githubhook');
var github = githubhook({
    host: '0.0.0.0',
    port: 3420,
    path: '/deploy/snake-client',
    secret: 'my-secret',
    logger: console,
});

github.listen();

github.on('snake-client:refs/heads/master', function (data) {
    // Exec a shell script
    var execOptions = {
        maxBuffer: 1024 * 1024 // Increase max buffer to 1mb
    };
    execFile('./deploy.sh', execOptions, function(error, stdout, stderr) {
        if (error) {
            console.log(error)
        }
    });
});
