function toJSONString(form) {
    var obj={};
    var elements = form.querySelectorAll("input, select, textarea");
    
    for(var i = 0; i < elements.length; ++i) {
        var element = elements[i];
        var name = element.name;
        var value = element.value;

        if(name) {
            obj[name] = value;
        }
    }
    return obj;
}

document.addEventListener( "DOMContentLoaded", function() {
    var form = document.getElementById("data");
    form.addEventListener("submit", function(e) {
        e.preventDefault();
        var json = toJSONString(this);
        
        const options = {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json;charset=utf-8'
            },
            body: JSON.stringify(json)
        }

        fetch('/', options)
            .then(res => res.json())
                .then(res => console.log(res))
                .catch(err => console.error(err));      
            
            setTimeout(function(){ 
                window.location.href = '/reboot'; 
            }, 1500);

        }, false);
});