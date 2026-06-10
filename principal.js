const carrousel = document.getElementById("carrousel");

let scrollSpeed = 1;

function autoScroll(){
    carrousel.scrollLeft += 0.75;

    // Reinicio invisible
    if(carrousel.scrollLeft >= carrousel.scrollWidth / 2){
        carrousel.scrollLeft = 0;
    }
}

setInterval(autoScroll, 10);

document.addEventListener('DOMContentLoaded', () => {
    const dotsContainer = document.getElementById('parallax-dots');
            
    // Factor de movimiento: mayor número = movimiento más brusco. Menor = más sutil.
    const movementFactor = 60; 

    document.addEventListener('mousemove', (e) => {
        // Calculamos el centro de la pantalla
        const centerX = window.innerWidth / 2;
        const centerY = window.innerHeight / 2;

        // Calculamos la posición del mouse relativa al centro
        const moveX = (e.clientX - centerX) / movementFactor;
        const moveY = (e.clientY - centerY) / movementFactor;

        // Aplicamos la transformación CSS (invertida para dar efecto de profundidad)
        dotsContainer.style.transform = `translate(${-moveX}px, ${-moveY}px)`;
    });
});
