mod timer;

use timer::Timer;

fn main() {
    let mut timer: Timer = Timer::new(10000);
    timer.start();
}
