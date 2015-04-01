F = module.exports = {}

# Return a function with THIS bound to `me`
F.bind = (f, me) -> (a...) -> f.apply me, a
