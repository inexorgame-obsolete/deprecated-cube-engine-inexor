node { 
    stage('Checkout project') {
        checkout scm
    }

    stage('Install and build dependencies') {
        dir('build') {
            sh 'conan install .. --build=missing'
        }
    }

    stage('Build with conan') {
        dir('build') {
            sh 'conan build ..'
        }
    }

    stage('Generating API documentation') {
        tool name: 'doxygen', type: 'hudson.plugins.doxygen.DoxygenInstallation'
        sh 'doxygen doxygen.conf'
        publishHTML(target: [
            allowMissing: false,
            alwaysLinkToLastBuild: false,
            keepAll: true,
            reportDir: 'doc/',
            reportFiles: 'index.html',
            reportName: 'Inexor Core API Documentation'
        ])
    }

    stage('Archive artifacts') {
        fingerprint 'bin/inexor,bin/inexor.exe,bin/RPCTreeData-inexor.proto'
        archiveArtifacts artifacts: 'bin/inexor,bin/inexor.exe,bin/RPCTreeData-inexor.proto', fingerprint: true, onlyIfSuccessful: true
    }

}
