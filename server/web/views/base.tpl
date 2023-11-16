<!doctype html>
<html lang="en" class="h-100">

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>IoT Project</title>

    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
    <style>
        .nav-masthead .nav-link {
            color: rgba(255, 255, 255, .5);
            background-color: transparent;
            border-bottom: .25rem solid transparent;
        }

        .nav-masthead .nav-link:hover,
        .nav-masthead .nav-link:focus {
            border-bottom-color: rgba(255, 255, 255, .25);
        }

        .nav-masthead .nav-link + .nav-link {
            margin-left: 1rem;
        }

        .nav-masthead .active {
            color: #fff;
            border-bottom-color: #fff;
        }
    </style>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.7.1/jquery.min.js"></script>

</head>

<body class="d-flex h-100">
    <div class="cover-container d-flex w-100 h-100 mx-auto flex-column">
        
        <header class="mb-auto bg-dark text-white p-3">
            <div>
                <h3 class="float-md-start mb-0">IoT Project - Weather Station</h3>
                <nav class="nav nav-masthead justify-content-center float-md-end">
                    <a id="nav-home" class="nav-link" href="/home">Home</a>
                    <a id="nav-about" class="nav-link" href="/about">About</a>
                </nav>
            </div>
        </header>

        <main class="p-3 text-center flex-grow-1 ">
            {{!base}}
        </main>

        <footer class="mt-auto text-end text-white-50 bg-dark">
            <div class="p-1 me-3">2023</div>
        </footer>
    
    </div>


   
    <script>
        var type = "{{nav}}";
        if (type == "about"){
            $("#nav-about").addClass("active");
            $("#nav-home").removeClass("active");
        }else{
            $("#nav-home").addClass("active");
            $("#nav-about").removeClass("active");
        }
    </script>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js" integrity="sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM" crossorigin="anonymous"></script>
    
</body>

</html>