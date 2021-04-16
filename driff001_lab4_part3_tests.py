tests = [ {'description': 'PINA: 0x00,PINB: 0x00 0x00 => PORTC: 0x00',
    'steps': [ {'inputs': [('PINA',0x00)], 'iterations': 5 } ],
    'expected': [('PORTB',0x00)],
    },
    {'description': 'PINA: 0x0F,PINB: 0x00 => PORTC: 0x02',
    'steps': [ {'inputs': [('PINA',0x0F)], 'iterations': 5 } ],
    'expected': [('PORTC',0x04)],
    },
    {'description': 'PINA: 0x0F,PINB: 0xF0 => PORTB: 0x08',
    'steps': [ {'inputs': [('PINA',0x0F)], 'iterations': 5 } ],
    'expected': [('PORTB',0x08)],
    },
    ]

