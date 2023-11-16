%import mqtt_client as mqtt

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no" />
    <title>IoT Project</title>
  </head>

<body> 
<H1>Hello World !</H1>

    <p> Topic : message</p>
% for k, v in mqtt.messages.items():
    <p>{{k}} : {{v}}</p>
% end
</body>

<script> 

window.setTimeout( function() {
    window.location.reload();
  }, 5000);

</script>