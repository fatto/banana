#include "input.hpp"

ProducerConsumerQueue<KeyEvent> Input::key_queue(64);
Signal<KeyEvent::KeyCode> Input::keyPress_signal;
Signal<KeyEvent::KeyCode> Input::keyRelease_signal;