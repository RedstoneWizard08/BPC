use std::time::Instant;

pub struct Timer {
    pub current: u128,
    pub last: u128,
    pub remaining: u128,
    pub total: u128,
    pub stopped: bool,
    pub needs_start: bool,
    pub start_time: Instant,
}

impl Timer {
    pub fn new(total: u128) -> Timer {
        return Timer {
            current: 0,
            last: 0,
            remaining: 0,
            total,
            stopped: true,
            needs_start: true,
            start_time: Instant::now(),
        };
    }

    pub fn format_time(time: u128) -> String {
        if time == 0 {
            return format!("{}s", time);
        }

        if time % 1000 == 0 {
            let s = time / 1000;
            if s % 60 == 0 {
                let m = s / 60;
                if m % 60 == 0 {
                    let h = m / 60;
                    return format!("{}h", h);
                } else {
                    return format!("{}m", m);
                }
            } else {
                return format!("{}s", s);
            }
        } else {
            return format!("{}ms", time);
        }
    }

    pub fn start(&mut self) {
        self.stopped = false;

        self.run();
    }

    fn write_current(&mut self) {
        let sd = "------------------------".to_string();
        let cp = "\nCurrent time: ";
        let rt = "\nRemaining time: ";
        let tt = "\nTotal time: ";
        let ed = "\n------------------------";

        let cur = Timer::format_time(self.current);
        let rem = Timer::format_time(self.remaining);
        let tot = Timer::format_time(self.total);

        let msg = sd + cp + &cur + rt + &rem + tt + &tot + ed;

        println!("{}", msg);
    }

    fn internal_run(&mut self) {
        if !self.stopped && self.current != self.total {
            if self.needs_start {
                self.start_time = Instant::now();
                self.needs_start = false;

                self.write_current();
            } else {
                let now = Instant::now().duration_since(self.start_time);
                self.current = now.as_millis();

                self.remaining = self.total - self.current;

                if self.current % 1000 == 0 && self.last != self.current {
                    self.last = self.current;

                    self.write_current();
                }
            }
        }
    }

    pub fn run(&mut self) {
        loop {
            if self.current == self.total {
                match system_shutdown::shutdown() {
                    Ok(_) => println!("Shutting down, bye!"),
                    Err(err) => eprintln!("Failed to shut down: {}", err),
                }

                break;
            } else {
                self.internal_run();
            }
        }
    }
}
