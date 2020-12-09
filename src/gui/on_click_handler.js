let spawn = require("child_process").spawn;

function organize(evt) {
    var source_directory_string = document.getElementById("source_directory_string").value;
    var output_directory_string = document.getElementById("output_directory_string").value;

    if (!source_directory_string && output_directory_string) {
        alert("source path is required");
    } else if (source_directory_string && !output_directory_string) {
        alert("output path is required");
    } else if (!source_directory_string || !output_directory_string) {
        alert("both source and output paths are required");
    } else {
        console.log("execution");
        let execution_spawn = spawn("../Mediarizer/mediarizer -h");
        // "./Users/keybraker/Github/Mediarizer/mediarizer -i " + source_directory_string + " -o " + output_directory_string);

        execution_spawn.stdout.on("data", (data) => {
            alert("data : " + data);
            console.log("data : " + data);
        });

        execution_spawn.stderr.on("data", (err) => {
            alert("err : " + err);
            console.log("err : " + err);
        });

        execution_spawn.on("exit", (code) => {
            alert("finished with: " + code);
            console.log("finished with: " + code);
        });
    }

}

function clear(evt) {
    document.getElementById("source_directory_string").value = "";
    document.getElementById("output_directory_string").value = "";
}

document.addEventListener('DOMContentLoaded', function() {
    document.getElementById("organize").addEventListener("click", organize);
    document.getElementById("clear").addEventListener("click", clear);
})