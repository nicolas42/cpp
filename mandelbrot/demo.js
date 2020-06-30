

function demo()
{
    let canvas = document.querySelector('canvas')
    canvas.width = 500;
    canvas.height = 500;

    var places_index = 0;
    let places = [
        { x: -0.6999687500000003, y: -0.2901249999999999, zoom: 1024 },
        { x: -0.027285156250000026, y: 0.6443066406250001, zoom: 2048 },
        { x: -0.027120712995529206, y: 0.6441158065199851, zoom: 67108864 },
        { x: -0.027099643200635935, y: 0.6440290103852749, zoom: 268435456 },
        { x: -0.02709963878151032, y: 0.6440290090395138, zoom: 4294967296 },
        { x: 0.31923687500000003, y: -0.4990148437499999, zoom: 1024000 },
        { x: 0.31923733207893373, y: -0.499014675590515, zoom: 8388608000 },
        { x: 0.38715883591593053, y: -0.25874134865963394, zoom: 1073741824 },
        { x: 0.1347109374999998, y: -0.6361328125, zoom: 2048 },
        { x: 0.2681601562500003, y: -0.004765624999999972, zoom: 4096 },
        { x: 0.38715883594200756, y: -0.2587413487062, zoom: 536870912 },
        { x: 0.32898730468750015, y: -0.4237490234374998, zoom: 16384 },
        { x: -1.7664619022752155, y: 0.041740019425749834, zoom: 1073741824, w: 800, h: 800, max_iterations: 855 },
    ]


    function draw_place() {
        mandelbrot_entity = places[places_index];
        draw_mandelbrot(canvas, mandelbrot_entity);
    }

    function get_parameters_from_url(vars, url) {
		// from https://html-online.com/articles/get-url-parameters-javascript/
		var parts = url.replace(/[?&]+([^=&]+)=([^&]*)/gi, function (m, key, value) {
			vars[key] = value;
		});
		return vars;
    }

    var mandelbrot_entity = { x: -0.6999687500000003, y: -0.2901249999999999, zoom: 1024 };
    get_parameters_from_url(mandelbrot_entity, window.location.href)
    draw_place();

    // Event Code
    var on_mousedown = function (e) {
        var x = mandelbrot_entity.x;
        var y = mandelbrot_entity.y;
        var zoom = mandelbrot_entity.zoom;

        if (e.which === 1) {
            // get position of clicked mouse cursor
            var rect = e.currentTarget.getBoundingClientRect();
            var x_pixel = e.clientX - rect.left;
            var y_pixel = e.clientY - rect.top;

            var math_height = 4 / zoom;
            var math_width = 4 / zoom;

            // update globals
            x = (x - math_width / 2) + x_pixel / ( canvas.width / math_width);
            y = (y - math_height / 2) + y_pixel / ( canvas.height / math_height);
            zoom *= 2;

        } else if (e.which === 3) { // right click
            zoom /= 2;
        }
        mandelbrot_entity = {x: x, y: y, zoom: zoom};
        draw_mandelbrot(canvas, {x: x, y: y, zoom: zoom});
    }

    canvas.addEventListener("mousedown", on_mousedown, false);
    canvas.addEventListener("contextmenu", (e) => { e.preventDefault(); });

    let buttons = document.querySelectorAll('button');
    buttons[0].addEventListener( "click", (e) => { places_index--; draw_place() }, false );
    buttons[1].addEventListener( "click", (e) => { places_index++; draw_place() }, false );


}