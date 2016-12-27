node { 
    stage "Checkout project"
    checkout scm

    stage 'Build'
    sh '[ -d build ] || mkdir build'
    sh 'cd build && conan install .. --build=missing && conan build ..'
}
