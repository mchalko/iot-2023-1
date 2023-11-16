% rebase('base.tpl', nav='about')

<div class="container mt-3">
    <div class="mt-4 p-5 bg-light text-black rounded">
      <h1>Weather Station</h1> 
      <p>
        This is a project for IoT course at university of Oulu. An m3 board located in a tesbed in France (iot-lab) is running RIOT and acquiring data, 
        sending it over the internet using ipv6 + dtls + coap all the way to the server. CoAP server, implemented by python aiocoap library, is 
        gathering data and saving it into a database using mongoDB. In the end the data is shown on this webpage using bottle framework and bootstrap.
        <p>
        <p class="fw-bold">Group members</p>
        <ul class="list-unstyled">
            <li>Miroslav Chalko</li>
            <li>Sehani Siriwardana</li>
            <li>Kuisma Hannuksela</li>
        </ul>
    </div>
</div>