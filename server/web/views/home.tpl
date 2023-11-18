% rebase('base.tpl', nav='home')

<div class="container mt-3">
    <div class="d-flex flex-wrap align-items-center justify-content-center gap-3">
    
        <div class="card p-2 align-self-stretch" style="width: 18rem;">
            <i class="card-img-top fa-5x fa fa-thermometer-empty text-danger" aria-hidden="true"></i>
            <div class="card-body">
              <h5 class="card-title">Temperature</h5>
              <p id="card-temp" class="card-text fs-1 fw-bold"></p>
            </div>
          </div>

          <div class="card p-2 align-self-stretch" style="width: 18rem;">
            <i class="card-img-top fa-5x fa fa-leaf text-success" aria-hidden="true"></i>
            <div class="card-body">
              <h5 class="card-title">Pressure</h5>
              <p id="card-pres" class="card-text fs-1 fw-bold"></p>
            </div>
          </div>
        </div>
        <div class="d-flex flex-wrap align-items-center justify-content-center gap-3 mt-3">

          <div class="card p-2 align-self-stretch" style="width: 18rem;">
            <i class="card-img-top fa-5x fa fa-sun-o text-warning" aria-hidden="true"></i>
            <div class="card-body">
              <h5 class="card-title">Light Intensity</h5>
              <p id="card-light" class="card-text fs-1 fw-bold"></p>
            </div>
          </div>

          <div class="card p-2 align-self-stretch" style="width: 18rem;">
            <i class="card-img-top fa-5x fa fa-clock-o" aria-hidden="true"></i>
            <div class="card-body">
              <h5 class="card-title">Last Seen</h5>
              <p id="card-time" class="card-text fs-1 fw-bold"></p>
            </div>
          </div>
    </div>
</div>

<script>

function load_data(){
    $.post("/get_data", "", function(data, status){
        $("#card-temp").text(data["temperature"] + " °C");
        $("#card-pres").text(data["pressure"] + " hPa");
        $("#card-light").text(data["light"] + " lux");  
    });

    $.post("/get_time", "", function(data, status){
        $("#card-time").text(data);
    });
}

$(document).ready(function(){
    load_data();
    setInterval(load_data, 2500);
});


</script>