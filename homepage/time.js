function time() {
    let now = new Date(), displayTime = "";
//Hours and Mins
    const time = [now.getHours(), now.getMinutes()];
    for (let i = 0; i < time.length; i++) {
        displayTime += updateTime(time[i]);
        if (i < time.length - 1) {
            displayTime += ":";
        }
    }
    document.getElementById("clock").innerText = displayTime;
}
time()
