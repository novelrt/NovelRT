do
    speaker "Narrator"
    speaker "Me"
    speaker "Abby"
    section "root"
        call "HelloWorld" { "Novel-chan presents a story!" }
    section "story"
        Narrator
            "It's only when I hear the sounds of shuffling feet and supplies being put away that I realize that the lecture's over."
            "Professor Madden's lectures are usually interesting, but today I just couldn't concentrate on it."
            "I've had a lot of other thoughts on my mind...thoughts that culminate in a question."
            "It's a question that I've been meaning to ask a certain someone."
            "When we come out of the university, I spot her right away."
            "I've known Sylvie since we were kids. She's got a big heart and she's always been a good friend to me."
            "But recently... I've felt that I want something more."
            "More than just talking, more than just walking home together when our classes end."
            "As soon as she catches my eye, I decide..."
        options
            "To ask her right away." { jump "askNow" }
            "To ask her later." { jump "askLater" }
    section "askNow"
        Abby
            "Hi there! How was class?"
        Me
            "Good..."
        Narrator
            "I can't bring myself to admit that it all went in one ear and out the other."
        Me
            "Are you going home now? Wanna walk back with me?"
        Abby
            "Sure!"
        jump "happy"
    section "askLater"
        Narrator
            "I can't get up the nerve to ask right now. With a gulp, I decide to ask her later."
        jump "sad"
    section "happy"
        Narrator
            "We get married shortly after that."
            "Our visual novel duo lives on even after we're married...and I try my best to be more decisive."
            "Together, we live happily ever after even now."
            "Good Ending."
    section "sad"
        Narrator
            "But I'm an indecisive person."
            "I couldn't ask her that day and I end up never being able to ask her."
            "I guess I'll never know the answer to my question now..."
            "Bad Ending."
end