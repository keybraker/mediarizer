let spawn = require("child_process").spawn;

let path = require('path');

function organize(evt) {
    let source_directory_string = document.getElementById("source_directory_string").value;
    let output_directory_string = document.getElementById("output_directory_string").value;

    if (!source_directory_string && output_directory_string) {
        alert("source path is required");
    } else if (source_directory_string && !output_directory_string) {
        alert("output path is required");
    } else if (!source_directory_string || !output_directory_string) {
        alert("both source and output paths are required");
    } else {
        const flags = [];

        flags.push("-i" + source_directory_string);
        flags.push("-o" + output_directory_string);

        if (document.getElementById("type_string").value)
            flags.push("-t" + document.getElementById("type_string").value);
        if (document.getElementById("recursive").checked)
            flags.push("-r");
        if (document.getElementById("photo").checked)
            flags.push("-p");
        if (document.getElementById("video").checked)
            flags.push("-v");
        if (document.getElementById("date").checked)
            flags.push("-D");
        if (document.getElementById("delete").checked)
            flags.push("-x");
        if (document.getElementById("move").checked)
            flags.push("-m");
        if (document.getElementById("verbose").checked)
            flags.push("-s");

        let terminal_output = "\n";
        const execution_spawn = spawn("/Users/keybraker/Github/Mediarizer/mediarizer", flags);

        execution_spawn.stdout.on("data", (data) => {
            terminal_output += data;
            document.getElementById("terminal_output").innerHTML = terminal_output;
        });

        execution_spawn.stderr.on("data", (err) => {
            alert("err : " + err);
        });

        execution_spawn.on("exit", (code) => {
            // alert(!code ? "Successfully organized library" : "Failed to organize library");
        });
    }

}

function clear(evt) {
    document.getElementById("source_directory_string").value = "";
    document.getElementById("output_directory_string").value = "";
    document.getElementById("terminal_output").innerHTML = "";
}

document.addEventListener('DOMContentLoaded', function() {
    document.getElementById("organize").addEventListener("click", organize);
    document.getElementById("clear").addEventListener("click", clear);
})