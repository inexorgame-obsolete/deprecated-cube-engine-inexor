node { 
    stage('Checkout project') {
        checkout scm
    }

    stage('Install and build dependencies') {
        steps {
            dir('build') {
                sh 'conan install .. --build=missing'
            }
        }
    }

    stage('Build with conan') {
        steps {
            dir('build') {
                sh 'conan build ..'
            }
        }
    }

    stage('Doxygen') {
        tool name: 'doxygen', type: 'hudson.plugins.doxygen.DoxygenInstallation'
    }

}
